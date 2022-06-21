FROM gcc:latest AS cpp  

ARG START_FROM_def=1
ENV START_FROM=$START_FROM_def

ARG END_WITH_def=15
ENV END_WITHv=$END_WITH_def

ARG RUN_OPT_def=gen
ENV RUN_OPT=$RUN_OPT_def 

ARG TOPS_OPT_def=150
ENV TOPS_OPT=$TOPS_OPT_def

COPY c++/src/. /usr/src/cpp_main
WORKDIR /usr/src/cpp_main

RUN g++ -pthread algorithmFloyd.cpp processor.cpp main.cpp parallel.cpp -o main


FROM sitespeedio/node:ubuntu-20.04-nodejs-14.15.0 AS build
ENV TARGETPLATFORM=linux/amd64
ARG TARGETPLATFORM=linux/amd64
WORKDIR /
COPY nodejs/backend/src/. ./app
RUN npm install --prefix app

COPY --from=cpp /usr/src/cpp_main /app
RUN apt-get update && apt-get install -y iputils-ping build-essential manpages-dev

EXPOSE 30501
CMD ["npm", "run", "start", "--prefix", "app"]