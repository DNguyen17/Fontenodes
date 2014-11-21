#include "XMLParser.h"

XMLParser::XMLParser()
{
    XMLDumpFile = nullptr;
    title = nullptr;
    id = 0;
    text = nullptr;
}

XMLParser::~XMLParser(){
    //delete myHandler;
    //delete myLookUpTable;

    if (XMLDumpFile != nullptr)
        delete[] XMLDumpFile;
    XMLDumpFile = nullptr;

    if (title != nullptr)
        delete[] title;
    title = nullptr;

    if (text != nullptr)
        delete[] text;
    text = nullptr;

    myParser.~XMLFileParser();
    doc.clear(); //deallocate memory pool of rapidxml class
}

//http://www.cplusplus.com/reference/istream/istream/read/
void XMLParser::setXMLDumpFile(string passedFile){

    if (XMLDumpFile != nullptr){
        delete[] XMLDumpFile;
        XMLDumpFile = nullptr;
    }

    ifstream ifs(passedFile);

    if (!ifs){

        cerr << "unable to open dump file" << endl;
        exit(1);
    }

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    XMLDumpFile = new char[length];

    ifs.read (XMLDumpFile,length);
    ifs.close();
}

//will cycle through all of XML documents in XML dump and index
//all of the words at first into a data structure. The data
//structure will then be saved off to hard memory for persistance
void XMLParser::storeOffXMLData(const char * DumpName){

    ofstream ofs(DumpName);
    int i = 1;
    ofstream fout("splitWords.txt");

    //loop through all files
    while (i <= 1){

        string fileName = "WikiDumpPart";
        fileName += to_string(i);
        fileName += ".xml";

        setXMLDumpFile(fileName);
        doc.clear();
        doc.parse<0>(XMLDumpFile);
        docNode = doc.first_node("mediawiki");
        xml_node<>* pageNode = docNode->first_node("page");

        //loop through all pages in one file
        while(pageNode !=0 ){

            myParser.setNodes(pageNode);

            title = new char[strlen(myParser.findTitle())+1];
            strcpy(title, myParser.findTitle());
            //ofs << "title: " << title << "\t";

            id = myParser.findPageID();
            //ofs << "id: " << id << endl;

            text = new char[strlen(myParser.findBodyText())+1];
            strcpy(text, myParser.findBodyText());
            //ofs << text << "\n" << endl;


            indexBodyOfText(text, id, fout);

            pageNode = pageNode->next_sibling("page");



            delete[] title;
            title = nullptr;

            //will not delete text once passed on to index functions
            delete[] text;
            text = nullptr;
            // // // // //

        }

        ++i;
    }

    ofs.close();
    fout.close();

}
//will store off author, title, ID, and XML file name in hard memory

void XMLParser::addPagesToLookup(){

}

void XMLParser::addSinglePageToLookup(){

}

void XMLParser::indexBodyOfText(char *body, int pageID, ofstream &fout){

    stringstream ss;
    ss << body;
    string buffer;
    //char* buffer = new char[strlen(body)]; //to be passed elsewhere, probably should not delete
    while (ss.peek() != EOF ){


        if (ss.peek() == '<'){ //get rid of XML nodes
            ss.ignore(strlen(body), '>');
        }

        else if ((ss.peek() < 48) || (ss.peek() >= 60 && ss.peek() < 65)
                 || (ss.peek() >= 91 && ss.peek() < 97) || ss.peek() >= 123){
            ss.ignore();
        }

        else {
            ss >> buffer;
            fout << buffer << endl;
        }
    }
    /*char* first = body;
    char* space = strchr(first, ' ');
    char* newline = strchr(first,'\n');
    char* tab = strchr(first, '\t');
    char* split = nullptr;

    while (space != nullptr){

        split = space;
        if ((newline < space) && newline != nullptr)
            split = newline;
        if ((tab < split) && tab != nullptr)
            split = tab;

        split[0] = '\0';

        fout << first << endl;

        first = split+1;
        newline = strchr(first, '\n');
        space = strchr(first, ' ');
        tab = strchr(first, '\t');
    }

    fout << first << endl;*/
    ss.flush();
    //delete[] buffer;

}
