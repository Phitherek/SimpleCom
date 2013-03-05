all:
	${CXX} ${CXXFLAGS} -o SCServer SCServer.cpp -lnetsocketpp
	${CXX} ${CXXFLAGS} -o SCViewer SCViewer.cpp -lnetsocketpp
	${CXX} ${CXXFLAGS} -o SCClient SCClient.cpp -lnetsocketpp
debug: 
	${CXX} ${CXXFLAGS} -o SCServer SCServer.cpp -lnetsocketpp -g
	${CXX} ${CXXFLAGS} -o SCViewer SCViewer.cpp -lnetsocketpp -g
	${CXX} ${CXXFLAGS} -o SCClient SCClient.cpp -lnetsocketpp -g
clean:
	rm -f SCServer SCViewer SCClient
