FROM gcc:latest
COPY ./src/. /usr/src/cpp_test
WORKDIR /usr/src/cpp_test
RUN g++ algorithmFloyd.cpp processor.cpp main.cpp -o Test
CMD ["./Test"]