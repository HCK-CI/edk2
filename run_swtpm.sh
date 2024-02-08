mkdir /tmp/mytpm4
swtpm socket --tpmstate dir=/tmp/mytpm4 --tpm2 --ctrl type=unixio,path=/tmp/mytpm4/swtpm-sock --log level=20 

