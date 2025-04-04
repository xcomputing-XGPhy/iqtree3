#!/bin/bash
if [ $# -eq 0 ];
then
   echo "Syntax: $0 [*-intel.tar.gz] [*-arm.tar.gz]"
   exit
fi

intelname=`basename $1 .tar.gz`
armname=`basename $2 .tar.gz`
universalname=`basename $1 -intel.tar.gz`

tar -xvf $1
tar -xvf $2
mkdir -p $universalname
mkdir -p $universalname/bin
cp $intelname/*.* $universalname

cp $intelname/bin/iqtree3 iqtree3_intel
cp $armname/bin/iqtree3 iqtree3_arm

# Create a zip containing both binaries
zip -vr binaries.zip iqtree3_intel iqtree3_arm

# Append the marker and the tar.gz to the script
cp linux_universal.sh tmp_linux_universal.sh
echo "__BINARY_START__" >> tmp_linux_universal.sh
cat  binaries.zip >> tmp_linux_universal.sh

# Make the final file executable
chmod +x tmp_linux_universal.sh
mv tmp_linux_universal.sh $universalname/bin/iqtree3

rm binaries.zip
rm -rf $intelname
rm -rf $armname
rm iqtree3_intel
rm iqtree3_arm

tar czf $universalname.tar.gz $universalname

rm -rf $universalname