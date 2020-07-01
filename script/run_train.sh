#!/bin/bash
cur_path=$(readlink -f $(dirname "$0"))
pre_path=${cur_path%/*}
modelPath=/tmp/kmeans.model
trainFile=
sh ${pre_path}/bin/kmeans_train -k 10 -n 10 -m $modelPath -t $trainFile
