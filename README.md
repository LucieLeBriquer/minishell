# minishell - documentation

1. [Sujet](#sujet)
2. [Notes](#notes)
3. [Description du programme](#description-du-programme)
4. [Ressources](#ressources)

## Sujet
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
- faire un `fork` pour chaque commande qui écrit sur la sortie standard, on close la sortie standard et on duplique l'output, donc lorsque qu'on écrira sur le fd 1 ça redirigera sur l'output désiré (same pour l'input)

### Astuces
- `lsof | grep "minishell"` : pour voir tous les fd ouverts par `minishell`, voir que tout est bien close à la fin de chaque commande

### Valeurs de retour

| Value | Signification |
|----:|:-------------|
| 1 | Catchall for general errors	impermissible operations |
| 2 | Misuse of shell builtins |
| 126	| Command invoked cannot execute (permission problem or not an executable) |
| 127	| Command not found |
| 128	| Invalid argument to exit |
| 128+n | Error signal n |
| 130	| Script terminated by Control-C |
| 255 | Exit status out of range |


## Description du programme
### Structure globale
1) **Analyse lexicale** : transforme les instructions en token
2) **Analyse syntaxique** : le parseur demande les tokens correspondant au fur et a mesure et construit un AST (cf partie suivante)
3) **Expansion** : remplace les alias, les variables d'environnement, ...
4) **Execution** : lecture de l'arbre suivant un parcours postfixe

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
Informations principales contenues dans les noeuds :
- input : fd depuis lequel on va lire
- output : fd sur lequel on va écrire
- start : position dans le split
- number : nombre d'arguments
- sep : token représentant le séparateur ou l'opérateur (`|`, `>`, `'`...)

#### Remplissage de l'arbre
Prenons comme exemple `A | B > C ; D`. On va construire l'arbre suivant :
```
        |
    A       ;
       B > C   D
```
Remplissage gauche puis droite. On aura donc toujours qu'un fils sans enfant à gauche. On va créer l'arbre selon le contenu de `split`. Lors de la création on va remplir les informations suivante : l'indice correspondant au noeud dans `split`, le nombre d'arguments composant la commande quand on se trouve sur une feuille (noeud sans enfant donc ici `A,B,C,D`), le type d'opérateur (`|` ou `;`) si l'on se trouve sur un noeud principal. Exemple :
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

Avant d'exécuter les commandes on a besoin de connaître input et output pour chaque noeud. On va parcourir à nouveau l'arbre pour remplir ces attributs.
- si on a un `|` appelle la fonction `pipe` qui va nous donner deux fd pour effectuer la liaison entre les commandes, on les donnera comme output au fils gauche et comme input au fils droit.
- lorsque l'on rencontre un `;` on remet l'input et l'output aux entrées et sorties standard (0 et 1)

### Expansion
Pour l'expansion, on étend les variables d'environnement lorsque `"` ou `' '` et on remplace `sep` dans la structure par `' '`. Attention à certains cas un peu tricky lorsque la variable correspond à un fichier de redirection :
```
lucie@lucie-XPS:~/Code/minishell$ var="file 2"
lucie@lucie-XPS:~/Code/minishell$ echo bl > $var
bash: $var: ambiguous redirect
```
Attention aussi à :
```
lucie@lucie-XPS:~/Code/minishell$ var="echo hey"
lucie@lucie-XPS:~/Code/minishell$ $var
hey
```

### Exécution
Lorsque l'on est sur une commande/feuille, on regarde le premier mot après expansion :
  - si c'est une commande built-in *go to la fonction dédiée*
  - si on commence par `./` on essaye de lancer l'exécutable `./name` *fork needed*
  - s'il y a un `=` on créé une variable d'environnement
  - sinon on essaye de lancer l'exécutable $(PATH)/name *fork needed*

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
#### exit
- `a` ou `a 1` ou `3.14` : `exit(2)` + erreur `numeric argument required`
- `1 a` ou `1 2` : pas d'exit + $? = 1 + erreur `too many arguments`
- si juste un argument numérique -> go le convertir % 256 et exit avec cette valeur

## Ressources
- https://shell.multun.net/structure.html
- https://shell.figarola.fr/x212.html
- https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe
- https://shell.figarola.fr/x54.html
- http://www.zeitoun.net/articles/communication-par-tuyau/start
- https://www.geeksforgeeks.org/fork-system-call/
