#!/bin/bash
cur_path=$(readlink -f $(dirname "$0"))
pre_path=${cur_path%/*}
modelPath=/tmp/kmeans.model
testFile=
resultFile=
sh ${pre_path}/bin/kmeans_predict -k 10 -n 10 -m $modelPath -p $testFile -r $resultFile
