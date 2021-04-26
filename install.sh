BUILD_FOLDER=./cmake-build-release
LIB_FOLDER=/usr/local/lib
INCLUDE_FOLDER=/usr/local/include

mkdir -p $BUILD_FOLDER
(cd $BUILD_FOLDER && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j 6 state_machine_cpp) || exit

if [ $? -eq 0 ]; then
  cp $BUILD_FOLDER/src/libstate_machine_cpp.so $LIB_FOLDER/libstate_machine_cpp.so
  mkdir -p $INCLUDE_FOLDER/state_machine_cpp
  (cd src/state_machine_cpp && tar cf ../../$BUILD_FOLDER/includes.tar.gz ./**/*.h)
  tar xf $BUILD_FOLDER/includes.tar.gz -C $INCLUDE_FOLDER/state_machine_cpp/
  rm $BUILD_FOLDER/includes.tar.gz
else
  echo "ERROR: could not install library"
fi
