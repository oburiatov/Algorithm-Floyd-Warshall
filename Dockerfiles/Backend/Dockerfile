FROM gcc:latest AS cpp  

ARG START_FROM_def=1
ENV START_FROM=$START_FROM_def

ARG END_WITH_def=15
ENV END_WITHv=$END_WITH_def

ARG RUN_OPT_def=gen
ENV RUN_OPT=$RUN_OPT_def 

ARG TOPS_OPT_def=150
ENV TOPS_OPT=$TOPS_OPT_def

COPY ./src/. /usr/src/cpp_main
WORKDIR /usr/src/cpp_main

RUN g++ algorithmFloyd.cpp processor.cpp main.cpp -o main

FROM ubuntu:18.04
COPY --from=cpp /usr/src/cpp_main /opt/cpp
RUN apt-get update && apt-get install -y iputils-ping build-essential manpages-dev
CMD ["ping","1.1.1.1"]

#ENTRYPOINT ./main $START_FROM $END_WITH $RUN_OPT $TOPS_OPT
