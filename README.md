# minishell

## Notes

## TODO

### buff reader
- si \ a la fin d'une ligne continuer le gnl
- lecture char par char puis :
	- \0 si delete
	- ctrl u : vide le buffer
	- fleche gauche, droit pour naviguer
	- comment gérer le curseur ?
- donc il va falloir un reader char par char, lorsque :
	- \n : on l'envoie comme avant
	- si la size du truc lu est nulle et que le ctrl-D est lancé on ne fait rien

### signaux
- pour le Ctrl+c, on doit return 130
- pour le dernier retour le mettre dans la variable begin ?

### exécution
- pour les executable faire un f/lstat pour savoir si executable ?
- penser à protéger les forks
- replacer l'ouverture d'un fd par lstat ou fstat

### gestion d'erreur
- plutôt que de faire des retours arbitraires faire un enum de types d'erreur à propager

## Some code

### lstat
Utilisation de lstat pour check si exécutable
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
