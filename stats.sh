#!/bin/bash
#
# Copyright (c) 2018, Intel Corporation
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Intel Corporation nor the names of its contributors
#       may be used to endorse or promote products derived from this software
#       without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

usage()
{
	echo ""
	echo "usage: `basename $0` [ARGS]"
	echo ""
	echo "-c number  ones based column number"
	echo "-f name    input file"
	echo "-h         show this message"
	echo "-l number  limit the number of records to process"
	echo ""
}

limit=0

while getopts :c:f:h:l: OPT; do
	case $OPT in
	c)
		column="$OPTARG"
		;;
	f)
		file="$OPTARG"
		;;
	h)
		usage
		exit 0
		;;
	l)
		limit="$OPTARG"
		;;
	*)
		usage
		exit 1
	esac
done

if [ -z "$column" ]; then
	echo "Need a column number."
	usage
	exit 1
fi

if [ -z "$file" ]; then
	echo "Need a file name."
	usage
	exit 1
fi

awk -v i=$column -v limit=$limit '
BEGIN {
	count = 0;
	mean = 0;
	M2 = 0;
}
!($1~/^\#/) {
	if (!count)
		min = max = $i;

	count++;
	delta = $i - mean;
	mean = mean + delta / count;
	M2 = M2 + delta * ($i - mean);

	if (min > $i)
		min = $i;
	if (max < $i)
		max = $i;

	if (count == limit)
		exit 0
}
END {
	variance_n = M2 / count
	variance = M2 / (count - 1)
	printf "min:    %+e\n", min;
	printf "max:    %+e\n", max;
	printf "pk-pk:  %+e\n", (max - min);
	printf "mean:   %+e\n", mean;
	printf "stddev: %+e\n", sqrt(variance);
	printf "count:   %u\n", count;
}
' $file

exit 0
