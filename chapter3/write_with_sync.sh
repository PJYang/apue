#!/usr/bin/env bash

echo "normal write to disk file"
time ../bin/write_with_sync_test normal < 3_4.sample
#real	0m0.756s
#user	0m0.004s
#sys	0m0.424s

echo "write to disk file followed by fdatasync"
time ../bin/write_with_sync_test fdatasync < 3_4.sample
#real	8m20.950s
#user	0m0.132s
#sys	0m4.844s

echo "write to_disk file followed by fsync"
time ../bin/write_with_sync_test fsync < 3_4.sample
#real	8m11.449s
#user	0m0.120s
#sys	0m5.172s



