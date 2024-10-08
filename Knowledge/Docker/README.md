# Docker Commands

## Docker network example

### Create docker network
- Creating docker network  mongo-network

#### start mongodb
``` docker
docker run -d \
-p 27017:27017 \
-e MONGO_INITDB_ROOT_USERNAME=admin \
-e MONGO_INITDB_ROOT_PASSWORD=password \
--net mongo-network \
--name mongodb \
mongo
```

### start mongo-express
```docker 
docker run -d \
-p 8081:8081 \ 
-e MONGO_INITDB_ROOT_USERNAME=admin \
-e MONGO_INITDB_ROOT_PASSWORD=password \
-e MONGO_INITDB_ROOT_SERVER=mongodb \
--net mongo-network \

```

----
# Create your own docker image

- be familier with the `Dockerfile` Syntax
- check that dummy example [Dockerfile](Dockerfile).
- be in same directory of Dockerfile
- run `docker build -t myfirstdockerimg:1.0 .`
    - as `myfirstdockerimg` image name and `.` is for the current directory

```bash
C:\Users\ahmed\Desktop>docker run -it b1d8f3226fb9 sh
/ #
/ #
/ #
/ # ls
bin    etc    lib    mnt    opt    root   sbin   sys    usr
dev    home   media  mydir  proc   run    srv    tmp    var
/ # cd mydir
/mydir #
```
```bash
/mydir # echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
/mydir # env
HOSTNAME=8a0c8ac49ce4
SHLVL=1
HOME=/root
OLDPWD=/
MONGO_DB_USERNAME=admin ####<<<<<<< yup
TERM=xterm
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
MONGO_DB_PWD=password ####<<<<<<< yup
PWD=/mydir 
```
- to remove all Docker containers, you can use the following command:
```batch
docker rm $(docker ps -a -q)
```


----


![alt text](asserts/image-1.png)

![alt text](asserts/image.png)

![je](asserts/MountingJenkinsContainer.png)

---

```bash
C:\Users\ahmed>docker volume inspect jenkins_home
[
    {
        "CreatedAt": "2024-08-04T03:58:11Z",
        "Driver": "local",
        "Labels": null,
        "Mountpoint": "/var/lib/docker/volumes/jenkins_home/_data",
        "Name": "jenkins_home",
        "Options": null,
        "Scope": "local"
    }
]
```


- interactive terminal with root user
```bash
docker run -it --rm -p 8085:8080 -p 50000:50000 --user root
```