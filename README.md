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

### exécution
- pour les executable faire un f/lstat pour savoir si executable ?
- penser à protéger les forks
- replacer l'ouverture d'un fd par lstat ou fstat

### gestion d'erreur
- plutôt que de faire des retours arbitraires faire un enum de types d'erreur à propager

### pipes et redirections
- des fd sont mals refermés (output ?)

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
