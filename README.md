# minishell

/bin/ls
/bin/ls -la
/bin/echo
/usr/bin/wc


echo hola
echo -n hola
echo -nnnn hola
echo -n -n -n hola
echo - hola
echo --n hola
echo -n- hola
echo -n-n hola
echo -n-n -n hola


exit hola
exit 0
exit
exit 256
exit 257


/bin/ls; echo $?
/bin/ls doesntexist; echo $?
/bin/lsa; echo $/


ctrl+c en linea vacia -> NL
ctrl+\ en linea vacia -> nada
ctrl+D en linea vacia -> exit

ctrl+c en linea no vacia -> NL
ctrl+\ en linea no vacia -> nada
ctrl+D en linea no vacia -> nada

ctrl+c en grep/cat -> exit 130
ctrl+\ en grep/cat -> exit 131
ctrl+D en grep/cat -> exit 0


echo "ls | grep a"
echo "ls >out"


echo '$PATH'
echo '$PWD >out'
echo '$USER | wc'


export ?=a -> error
export _a=a -> OK
export 1a=a -> error
export a1=a -> OK
export a=a=a -> a = 'a=a'
export a?=a -> error
export a=a b=b c=c d=d -> OK    (si falla alguno (ej: 1b=b) los que se hayan ejecutado antes se exportan igualmente)


unset a
unset a b c
(no comprobar input, hacer unset pueda existir o no)


cd								-> debe ir a $HOME
cd -							-> debe ir a OLDPWD
cd /bin
cd ../
cd /bin/ls 						-> not a directory
cd (en una carpeta en el limbo)	-> llevar a home aunque getcwd falle


ls
wc
cat
grep
(probar sin PATH)


<doesntexist wc				-> error
ls >out						-> crear out y redirigir output
ls >out >out2				->crear out y out2, redirigir output a out2
<in grep a >out				->leer de in y redirigir output a out
<in1 <in2 cat >out1 >out2	->leer in1 y in2, redirigir input de in2, crear out1 y out2, redirigir output a out2

< cat						->error de apertura
<README.md					->nada
ls >						->error de apertura
>out						->crear archivo

cat hola >>out				->crear el archivo
cat que tal >>out			->no eliminar los contenidos previos y escribir input

<<							->ejecutarse y espera una linea vacia ("\0")
<<<							->error
cat << hola					->volver a mostrar todo lo que hayas escrito hasta hola
<< hola cat					->volver a mostrar todo lo que hayas escrito hasta hola
<< '$HOME'					->no debe expandir $HOME
<< "$USER"					->no debe expandir $USER
<< $USER					->no debe expandir $USER

cat <README.md | grep '$USER' | wc -l
cat | cat | ls


