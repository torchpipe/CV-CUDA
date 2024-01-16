apt-get update -y
  apt-get install -y  ninja-build  libssl-dev wget
 
wget https://cmake.org/files/v3.20/cmake-3.20.1-linux-x86_64.tar.gz -O /tmp/cmake-3.20.1-linux-x86_64.tar.gz
 cd /tmp
 tar zxvf cmake-3.20.1-linux-x86_64.tar.gz
mv cmake-3.20.1-linux-x86_64 /opt/cmake-3.20.1
ln -sf /opt/cmake-3.20.1/bin/*  /usr/bin/
cd -