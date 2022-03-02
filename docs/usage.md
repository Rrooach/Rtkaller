
## Build

### Install golang
We use golang in Rtkaller, so make sure golang is installed before build Rtkaller
``` bash
wget https://dl.google.com/go/go1.14.2.linux-amd64.tar.gz
tar -xf go1.14.2.linux-amd64.tar.gz
mv go goroot
mkdir gopath
export GOPATH=`pwd`/gopath
export GOROOT=`pwd`/goroot
export PATH=$GOPATH/bin:$PATH
export PATH=$GOROOT/bin:$PATH
```

### install Rtkaller
during build Rtkaller, we use __go mod__, __make__ and __git__.
``` bash
cd Rtkaller/
go mod vendor
make -j32
```

### Prepare RTOS Kernel
In here we use RT-linux v5.9 as an example.
First we need to have have a compilable RTOS
```bash
#download linux kernel 
git clone https://github.com/torvalds/linux
cd linux
export Kernel=$pwd
git checkout -f a1b8638ba132

# download rt-linux patches
wget https://mirrors.edge.kernel.org/pub/linux/kernel/projects/rt/5.9/older/patch-5.9-rc7-rt10.patch.xz 

# patch it 
xz -d patch-5.9-rc7-rt10.patch.xz 
git apply patch-5.9-rc7-rt10.patch
```

After we have the RTOS, we need to compile it.
``` bash
# modified configuration
make defconfig  
make kvmconfig

vim .config
```

``` vim
# modified configuration
CONFIG_PREEMPT=y
CONFIG_PREEMPT_RT_BASE=y
CONFIG_HAVE_PREEMPT_LAZY=y
CONFIG_PREEMPT_LAZY=y
CONFIG_PREEMPT_RT_FULL=y
CONFIG_PREEMPT_COUNT=y

CONFIG_KCOV=y 
CONFIG_DEBUG_INFO=y 
CONFIG_KASAN=y
CONFIG_KASAN_INLINE=y 
CONFIG_CONFIGFS_FS=y
CONFIG_SECURITYFS=y
```

make it!
```
make olddefconfig
make -j32
```

Now we should have vmlinux (kernel binary) and bzImage (packed kernel image):
```bash
$ ls $KERNEL/vmlinux
$KERNEL/vmlinux
$ ls $KERNEL/arch/x86/boot/bzImage
$KERNEL/arch/x86/boot/bzImage
```

### Prepare Image
 
```bash 
sudo apt-get install debootstrap 
export IMAGE=$pwd
cd $IMAGE/
wget https://raw.githubusercontent.com/google/syzkaller/master/tools/create-image.sh -O create-image.sh
chmod +x create-image.sh
./create-image.sh
```
now we have a image stretch.img and a public key


### Ready QEMU
Install QEMU:
``` bash
sudo apt-get install qemu-system-x86
```
Make sure the kernel boots and sshd starts:
``` bash 
qemu-system-x86_64 \
	-m 2G \
	-smp 2 \
	-kernel $KERNEL/arch/x86/boot/bzImage \
	-append "console=ttyS0 root=/dev/sda earlyprintk=serial net.ifnames=0" \
	-drive file=$IMAGE/stretch.img,format=raw \
	-net user,host=10.0.2.10,hostfwd=tcp:127.0.0.1:10021-:22 \
	-net nic,model=e1000 \
	-enable-kvm \
	-nographic \
	-pidfile vm.pid \
	2>&1 | tee vm.log
```
see if ssh works
``` bash 
ssh -i $IMAGE/stretch.id_rsa -p 10021 ``-o "StrictHostKeyChecking no" 
```

To kill the running QEMU instance press Ctrl+A and then X or run:
``` bash
kill $(cat vm.pid)
```
If QEMU works, the kernel boots and ssh succeeds, we can shutdown QEMU and try to run Rtkaller.

## Usage

Now we can start to 
prepare a __config.json__ file.

move to Rtkaller directory

``` json 
{
        "target": "linux/amd64",
        "http": "127.0.0.1:56295",
        "workdir": "./workdir",
        "cover": false,
        "kernel_obj": "$(Kernel)/vmlinux",
        "image": "$(image)/stretch.img",
        "sshkey": "$(image)/stretch.id_rsa",
        "syzkaller": "$pwd",
        "procs": 2,
        "type": "qemu",
        "vm": {
                "count": 2,
                "kernel": "$(Kernel)/bzImage",
                "cpu": 2,
                "mem": 4096
        }


```

Now run it

``` bash
./bin/syz-manager -config config.json
```

