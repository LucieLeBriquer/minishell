#!/bin/bash

## Partie Obligatoire

### Commande simple
/bin/ls

### Arguments
/bin/ls --color /
/bin/ls nothing

### Echo
echo hey"you"
echo "hey    you"
echo -n hey"you"
echo -n -n -n -n hey -n 42


### Exit
exit
exit 12
exit 1 a
exit ab 1

### Valeur de retour d'un processus
echo hey ; echo $?
/bin/ls fichiernul ; echo $?
a=b c=d notfound1 | echo $? $a | notfound2 ; echo $? ; echo $?

### Point virgule
ls ; echo hey
ls;echo hey

### Signaux 
#Essayez ctrl-C dans un prompt vide
#Essayez ctrl-\ dans un prompt vide
#Essayez ctrl-D dans un prompt vide
#Essayez ctrl-C dans un prompt après que vous ayiez écrit des choses
#Essayez ctrl-D dans un prompt après que vous ayiez écrit des choses
#Essayez ctrl-\ dans un prompt après que vous ayiez écrit des choses
#Essayez ctrl-C après avoir lancé une commande bloquante, comme cat ou grep sans argument
#Essayez ctrl-\ après avoir lancé une commande bloquante, comme cat ou grep sans argument
#Essayez ctrl-D après avoir lancé une commande bloquante, comme cat ou grep sans argument
#Répetez plusieurs fois en utilisant des commandes différentes

### Guillemets
/bin/echo a"bc      def\"g\" " "hi ; j"

### Env
env
new="hey"; env

### Export
export new; env
OLDPWD="lost"; env

### Unset
export new="i'm here"; echo $new; unset new; echo $new

### Variable d'environnement
test="echo    hey"
$test
echo $test
echo "$test"
"$test"

### Pwd
pwd
pwd .
pwd ..
pwd a b cd e

### Path relatif
../../../../bin/ls
./minishell

### Path d'environnement
ls | wc -c
unset PATH
ls
PATH="directory1"
ls
PATH="directory1:directory2:/bin"
ls

### Simple quotes
echo 'this is "a simple $test   ;  ' | cat -e

### Redirection
echo hey > file ; cat file
filename="two parts"
echo hey > $filename
echo hey >> file ; cat file
cat < file > copy ; cat copy
echo test > file1 > file2 > file3; tail file1 file2 file3 ; rm file1 file2 file3
> bl echo hey; cat bl
echo hey >file10
echo Bonjour >file1 jeune homme; cat file1
echo Bonjour >file1 jeune homme > file2 ca va >file3; tail file1 file2 file3 ; rm file1 file2 file3
ls | echo OK
ls | echo bonjour > file11 | ls
ls | hexdump > f0 | echo Bonjour >f1 jeune homme > f2 ca va >f3 | ls
echo bonjour >f1 mec >f2 | echo ok > f3 | echo >f4 >>f5 oui | echo final >f7
filename="file_test" ; echo "hi Bro" > $filename
echo hey >> file ; hexdump file | cat
echo hey >> file ; hexdump file | cat -e
echo test > file01 > file02 > file03 ; tail file01 file02 file03
> b1 echo hey lucie ; cat b1

### Pipes
cat file | grep hey | more
ls fichiernul | grep bla | more

### Autres
sleep 5 | sleep 5 | sleep 5 | sleep 5 | sleep 5
sleep 5 | sleep 5 | sleep 5 ; sleep 5
