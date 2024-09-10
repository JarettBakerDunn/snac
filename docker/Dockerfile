FROM ubuntu:jammy

RUN apt-get update && \
  DEBIAN_FRONTEND='noninteractive' \
  DEBCONF_NONINTERACTIVE_SEEN='true' \
  apt-get install --yes \
    gfortran \
    build-essential \
    git \
    python2 \
    libxml2-dev \
    libgsl-dev \
    curl \
    libmpich-dev \
    mpich \
    subversion \
    libapache2-mod-svn \
    libc6-dev \
    doxygen


RUN useradd \
--create-home \
snac_user

WORKDIR /home/snac_user

USER snac_user

ENV FFLAGS="-w -fallow-argument-mismatch -O2"

RUN curl -L -O "https://www.mpich.org/static/downloads/1.5rc3/mpich2-1.5rc3.tar.gz"; tar -xvf mpich2-1.5rc3.tar.gz; cd mpich2-1.5rc3; ./configure --prefix=/home/snac_user/mpich2-install 2>&1 | tee c.txt; make 2>&1 | tee m.txt; make install 2>&1 | tee mi.txt; export PATH=/home/you/mpich-install/bin:$PATH;

ENV MPI_INCDIR=/home/snac_user/mpich2-1.5rc3/src/include

RUN git clone 'https://github.com/jarettbakerdunn/snac.git'; cd snac; git checkout devel;

ENV CC=mpicc
ENV CXX=mpicxx

#RUN cd snac; cd docker; mv configure.sh /home/snac_user/snac; cd ..; chmod +x configure.sh;
