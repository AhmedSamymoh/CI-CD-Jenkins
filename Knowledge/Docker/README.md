# Docker Commands

## Docker network example
-----

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