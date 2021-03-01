# minishell - documentation
- [Travail attendu](#travail-attendu)
- [TODO](#todo)
- [Notes](#notes)
  - [Fonctions autorisées](#fonctions-autorisées)
  - [Processus](#processus)
  - [Astuces](#astuces)
- [Plan d'attaque](#plan-dattaque)
- [Plus en détail](#plus-en-détail)
  - [Gestion de l'environnement](#gestion-de-lenvironnement)
  - [Parsing de la commande](#parsing-de-la-commande)
  - [Construction de l'AST](#construction-de-last)
  - [Extension](#extension)
  - [Exécution](#exécution)
  - [Description des commandes builtin](#description-des-commandes-builtin)
- [Ressources](#ressources)

## Travail attendu
Écrivez un shell qui doit :
- Afficher un prompt en l’attente d’une nouvelle commande
- Chercher et lancer le bon executable (basé sur une variable d’environnement `PATH` ou en utilisant un path absolu), comme dans `bash`
- Vous devez implémenter les builtins suivants :
  - `echo` et l’option `-n`
  - `cd` uniquement avec un chemin absolu ou relatif
  - `pwd` sans aucune option
  - `export` sans aucune option
  - `unset` sans aucune option
  - `env` sans aucune option ni argument
  - `exit` sans aucune option
- `;` dans la ligne de commande doit séparer les commandes
- `'` et `"` doivent marcher comme dans bash, à l’exception du multiligne
- Les redirections `<`, `>`et `>>` doivent marcher comme dans bash, à l’exception des aggrégations de fd
- `|` doit marcher comme dans bash
- Les variables d’environnement (`$variable`) doivent marcher comme dans bash
- `$?` doit marcher comme dans bash
- `ctrl-C`, `ctrl-D` et `ctrl-\` doivent afficher le même résultat que dans bash

## TODO
### General
- [done] un split qui prend en compte les `'` et `"`
  - pour les simples quotes : easy
  - pour les doubles c'est plus galère, il faut check tous les cas de `\` et `$`
- [done] la création de noeuds à chaque opérateur `|,>,>>,<,;`
- [done] affichage du prompt et attente d'une commande
- [done] création d'une liste chaînée à partir de l'environnement et une fonction de recherche dans cette liste
- [done] fonction d'expansion d'une commande simple
- [done] parcours de l'arbre pour remplir les fd d'`intput` et d'`output` a chaque noeud principal avec un appel a `pipe`
- [done] faire des tests fork, pipe pour etre sure de tout bien comprendre
- [done] se renseigner sur les signaux qui peuvent etre envoyes pendant l'execution d'un processus pour gerer les leaks (par exemple deja ctrl+c ctrl+d dans la fonction principale)
- [done] rajouter un entier d'état pour savoir si la commande est exportée ou non ; est-ce que l'on doit modifier l'environnement extérieur ?
- [done] faire les commandes built-in pour commencer
### En detail (a suppr au fur et a mesure)
- pour le Ctrl+c, on doit return 130
- plutôt que de faire des retours arbitraires faire un enum de types d'erreur à propager
- gestion du dernier retour à faire : le mettre dans la variable begin ?
- rebosser le export en faisant une liste chainee des variables à exporter
- same pour les définitions de variables temporaires (suivies d'une commande ?)

## Notes

### Fonctions autorisées
- `fork` : créé un nouveau processus enfant
- `wait` : attend un signal d'arrêt d'un processus, wait4 pour attendre la fin d'un processus précis
- `exit` : termine le processus
- `getcdw` : pour obtenir le pwd
- `stat` : donne toutes les infos d'un fichier comme un ls
- `lstat` : same sauf que dans le cas d'un lien donne les infos sur le lien et pas le fichier pointé
- `ftat` : donne toutes les infos sur un fichier comme un ls, mais cette fois on lui passe en argument le file descriptor
- `kill` : envoie un signal d'arrêt au processus indiqué
- `signal(sig, fun)` : exécute `fun` si `sig` est reçu
- `execve` : exécuter un exécutable, avec ses arguments et l'environnement en paramètres
- `dup` : duplique le descripteur d'un objet, i.e. attribue un nouveau descripteur qui pointe vers le même objet, ainsi lorsque l'on read sur l'un on avance sur les deux
- `dup2` : permet en plus de spécifier la valeur du descripteur
- `chdir` :  change le répertoire courant
- `opendir` : ouvre le fichier descriptif du dossier
- `readdir` : lit l'entrée suivante dans le fichier descriptif du dossier
- `closedir` : referme le ficher descriptif du dossier
- `pipe` : rempli un tableau avec deux nouveaux file descriptors qui vont être utiles pour changer l'entrée standard et la sortie standard

### Processus
- il y a des commandes suffisamment simples pour être exécutées directement par minishell ce sont les *commandes builtin*
- a contrario les *commandes externes* doivent etre exécutées dans un nouveau processus et nécessitent donc un `fork`
- faire un `fork` pour chaque commande qui écrit sur la sortie standard, on close la sortie standard et on duplique l'output, donc lorsque qu'on écrira sur le fd 0 ça redirigera sur l'output désiré (same pour l'input)

### Astuces
- `lsof | grep "minishell"` : pour voir tous les fd associés, voir que tout est bien close à la fin de chaque commande
- utilisation de `lstat` pour check si exécutable
```
#include <sys/stat.h>

int	main(int argc, char **argv)
{
	char		*file;
	struct stat	buf;
	int			err;

	file = argv[argc - 1];
	err = lstat(file, &buf);
	if (err == 0 && buf.st_mode & S_IXUSR)
		printf("executable\n");
	return (0);
}
```

## Plan d'attaque
1) **Analyse lexicale** : transforme les instructions en token
2) **Analyse syntaxique** : le parseur demande les tokens correspondant au fur et a mesure et construit un AST (cf partie suivante)
3) **Expansion** : comme son nom l'indique, remplace les alias, les variables d'environnement, ...
4) **Execution** : lecture de l'arbre par un parcours postfixe

## Plus en détail

### Gestion de l'environnement
On va créer une liste chaînée à partir de l'environnement contenant à chaque maillon le nom de la variable et sa valeur.

### Parsing de la commande
On split selon les quotes et les opérateurs rencontrés. On construit un tableau de structure `split` avec comme attribut le caractère séparateur ainsi que la chaîne contenue entre les deux délimiteurs.
```
mini@shell /home/lucie/Code/minishell$  that 's' a | "  \"wonderfuuul" >$tree  ;with '"an' |AMAZING     parsing
[ ] [that]
['] [s]
[ ] [a]
[|] [|]
["] [  \"wonderfuuul]
[>] [>]
[ ] [$tree]
[;] [;]
[ ] [with]
['] ["an]
[|] [|]
[ ] [AMAZING]
[ ] [parsing]
```

### Construction de l'AST
#### Format des noeuds
- entry point
- exit point
- position dans le split
- opérateur (0 si simple commande)
- fils gauche
- fils droit

#### Remplissage de l'arbre
Prenons comme exemple `A | B > C ; D`. On va construire l'arbre suivant :
```
        |
    A       ;
       B > C   D
```
Remplissage gauche puis droite. On aura donc toujours qu'un fils sans enfant à gauche. On va creer l'arbre selon notre premier parsing contenu dans `split`. Lors de la création on va remplir les informations suivante : l'indice correspondant au noeud dans `split`, le nombre d'arguments composant la commande quand on se trouve sur une feuille (noeud sans enfant donc ici `A,B,C,D`), le type d'opérateur (`|` ou `;`) si l'on se trouve sur un noeud principal. Exemple :
```
mini@shell /home/lucie/Code/minishell$  that 's' a | "  \"wonderfuuul" >$tree  ;with '"an' |AMAZING     parsing
[ ] [that]
['] [s]
[ ] [a]
[|] [|]
["] [  \"wonderfuuul]
[>] [>]
[ ] [$tree]
[;] [;]
[ ] [with]
['] ["an]
[|] [|]
[ ] [AMAZING]
[ ] [parsing]

--- parcours postfixe de l'arbre ---
type : 0	0[3]	operator :  	that s a 
type : 1	3[1]	operator : |	| 
type : 0	4[3]	operator : "	  \"wonderfuuul > $tree 
type : 5	7[1]	operator : ;	; 
type : 0	8[2]	operator :  	with "an 
type : 1	10[1]	operator : |	| 
type : 0	11[2]	operator :  	AMAZING parsing 

--- recursive execution ---
input 0		output 3		that s a 
input 4		output 1		  \"wonderfuuul > $tree 
input 0		output 5		with "an 
input 6		output 1		AMAZING parsing 
```

Avant d'exécuter les commandes on a besoin de connaître les entry point et exit point de chaque noeud. On va parcourir à nouveau l'arbre pour remplir ces attributs à chaque noeud.
- si on a un `|` appelle la fonction `pipe` qui va nous donner un entry point `fd_e` et un exit point `fd_s`. que l'on donnera comme exit point au fils gauche et comme entry point au fils droit.
- lorsque l'on rencontre un `;` on remet l'entry point et l'exit point aux entrées et sorties standard (0 et 1)
- par défaut l'entry point = 0 et l'exit point = 1

### Extension
Pour l'extension, on étend les variables d'environnement lorsque `"` ou `' '` et on remplace `sep` dans la structure par `' '`. Maybe faire du réalloc.

### Exécution
Lorsque l'on est sur une commande ('A', 'B', 'C' ou 'D') donc que le séparateur est `' '`, on regarde le premier mot
  - si c'est une commande built-in (*go to la fonction dédiée*)
  - si on commence par `./` on essaye de lancer l'exécutable `./name` *fork needed*
  - sinon s'il y a un `=` on créé une variable d'environnement
  - sinon on essaye de lancer l'exécutable $(PATH)/name (check si on a besoin de tester dans l'ordre ou si execve s'en charge directement) *fork needed*

Informations nécessaires à l'exécution des commandes implémentées dans `minishell` :
- pour `echo` :
  - les indices de début et de fin dans split des arguments de `echo`
  - option `-n` ou non
- pour `cd` : l'indice du path à regarder
- pour `pwd` : nada
- pour `export` : indice de la variable à exporter (si la recherche retourne NULL on ne fait rien, pas d'erreur)
- pour `unset` :  : indice de la variable à désexporter (si la recherche retourne NULL on ne fait rien, pas d'erreur ; attetion ne la supprime pas elle est toujours définie)
- pour `env`: nada
- `exit` : nada
Pour resumer, pour executer une commande il nous faut l'indice du debut du/des arguments, le nombre d'arguments a prendre en compte, un autre entier pour l'option d'`echo` ainsi que les `fd` d'input et d'output.

### Description des commandes builtin
#### echo
- prend en argument l'ensemble des chaînes de caractères en suivant, attention au cas où les arguments ne sont pas séparés par un espace :
```
lucie@lucie-XPS ~/Code/minishell$ echo "'"'$a'"'" 
'$a'
lucie@lucie-XPS ~/Code/minishell$ echo "'"    '$a'     "'" 
' $a '
```
- si on a une redirection `<` tente d'ouvrir le fichier mais ignore son contenu, donc lève une exception si le fichier n'existe pas par exemple
- pour l'option `-n` :
```
lucie@lucie-XPS ~/Code/minishell$ echo -n "-n" 
lucie@lucie-XPS ~/Code/minishell$ echo -n -n '-n' -n 
lucie@lucie-XPS ~/Code/minishell$ echo -n -n -n -n "hey"
hey%
lucie@lucie-XPS ~/Code/minishell$ echo -n "hey " -n -n -n "hey" 
hey  -n -n -n hey%
```

## Ressources
- https://shell.multun.net/structure.html
- https://shell.figarola.fr/x212.html
- https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe
- https://shell.figarola.fr/x54.html
- http://www.zeitoun.net/articles/communication-par-tuyau/start
- https://www.geeksforgeeks.org/fork-system-call/
