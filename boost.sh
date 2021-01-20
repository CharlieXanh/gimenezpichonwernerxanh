#launch boost tests
#./build/test/shared/test_shared_dummy
echo "********************************************************************"
echo "BOOST STATE"
echo ""
./build/test/shared/test_shared_state
echo ""
echo "********************************************************************"
echo "BOOST ENGINE"
echo ""
./build/test/shared/test_shared_engine
echo ""
echo "********************************************************************"
echo "BOOST CLIENT"
echo ""
./build/test/client/test_client_dummy
