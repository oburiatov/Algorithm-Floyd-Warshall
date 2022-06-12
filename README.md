#Run C++ project with variables
docker run --rm -it -e "START_FROM=1" -e "END_WITH=5" -e "RUN_OPT=gen" -e "TOPS_OPT=150" algorithm-floyd-backend

#Run docker container on Ubuntu with C++ project
docker run -it -d algorithm-floyd-backend

