FROM gcc:latest

ARG START_FROM=5
ENV START_FROMv=$START_FROM 

ARG END_WITH
ENV END_WITHv="49"

ARG RUN_OPT
ENV RUN_OPTv=$RUN_OPT 

ARG TOPS_OPT
ENV TOPS_OPTv=$TOPS_OPT

COPY ./src/. /usr/src/cpp_test
WORKDIR /usr/src/cpp_test
RUN g++ algorithmFloyd.cpp processor.cpp main.cpp -o Test
CMD ["./Test", "5", "${END_WITH}", "${END_WITH}", "${END_WITH}"]
