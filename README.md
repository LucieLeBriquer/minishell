# minishell

## Notes
- si \ a la fin d'une ligne continuer le gnl

- dans les doubles quotes le backslash utile pour
	- \
	- $
	- "

## TODO

### env
- export n'affiche pas la variable "\_="

### expansion
- pour l'expansion des db quotes, supprimer tous les escaping + $ a replace, si search = null on skip
- pendant l'expansion remplacer '\' 'n' par '\n' etc pour tous les caractères echappés

### exécution
- pour les executable faire un f/lstat pour savoir si executable .
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
