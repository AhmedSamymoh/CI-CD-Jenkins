FROM alpine

ENV MONGO_DB_USERNAME=admin \
    MONGO_DB_PWD=password

RUN echo "MongoDB Username: $MONGO_DB_USERNAME"
RUN echo "MongoDB Password: $MONGO_DB_PWD"

RUN mkdir mydir



WORKDIR /home/mydir 
# WORKDIR /home/mydir : change the working directory to /home/mydir.

RUN npm install
# RUN npm install : install the dependencies of the project.

CMD [ "node", "app.js" ]
# CMD [ "node", "app.js" ] : execute the command node app.js to start the application.


