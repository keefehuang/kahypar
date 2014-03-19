#!/bin/bash

taskfilename=current_opt.tasks
subdir=current_opt_simple_stop
reps=10

epsilon=0.02
nruns=10
vcycles=10
ctype=heavy_heuristic
cmaxnet=-1
s=0.0375
t=170
stopFM=simple
FMreps=-1
i=190
alpha=14
dbname=current_opt_simple.db
rtype=twoway_fm

GRAPH_DIR=/home/schlag/repo/schlag_git/benchmark_instances/
RESULT_DIR=/home/schlag/repo/schlag_git/benchmark/results/$(date +%F)"_"$subdir
PARTITIONER=/home/schlag/repo/schlag_git/release152/src/application/KaHyPar

if [ ! -d $RESULT_DIR ]
then
    mkdir $RESULT_DIR
fi

dbname=$RESULT_DIR"/"$dbname
taskfilename=$RESULT_DIR"/"$taskfilename

cd $GRAPH_DIR
for file in *.hgr;
do
  for run in $(seq 1 $reps)
  do
    seed=`od -A n -t d -N 2 /dev/urandom | awk '{print $1}'`
    echo "$PARTITIONER --hgr=$GRAPH_DIR$file --e=$epsilon --seed=$seed --nruns=$nruns --vcycles=$vcycles --cmaxnet=$cmaxnet --ctype=$ctype --s=$s --t=$t --stopFM=$stopFM --FMreps=$FMreps --i=$i --alpha=$alpha --rtype=$rtype --db=$dbname" >> $taskfilename
  done  
done
