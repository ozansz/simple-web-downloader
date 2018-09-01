echo -e "[+] Installing dependencies...\n"

sudo apt-get install libcurl4 libcurl4-gnutls-dev

echo -ne "\n[+] Compiling..."

gcc -o simple-get simple-get.c sg_lib.c $(pkg-config --cflags --libs libcurl)

echo "DONE."
