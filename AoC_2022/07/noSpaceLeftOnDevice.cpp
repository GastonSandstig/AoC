#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/07/input.txt";

class Dir;

class DirContent{
    public:
        string name;
        virtual int size(){return 0;}
        Dir* getParent(){return parent;}
        void setParent(Dir* p){parent = p;}
        virtual ~DirContent(){}
    protected:
        Dir* parent;
};

class File: public DirContent{
    public:
        int size(){
            return filesize;
        }
        File(string n = "", int fsize = 0){
            name = n;
            filesize = fsize;
        }
    private:
        int filesize;
};

class Dir: public DirContent{
    public:
        int size(){
            int s = 0;
            for(Dir* f : subdirs)
                s += f->size();
            for(File* f : subfiles)
                s += f->size();
            return s;
        }
        const vector<Dir*> findBySize(int cutoff = INT_MAX){
            
            if(subdirs.size() < 1)
                return {};
            
            vector<Dir*> foundDirs;
            for(Dir* f : subdirs){
                vector<Dir*> tmp = f->findBySize(cutoff);
                foundDirs.insert(foundDirs.begin(), tmp.begin(), tmp.end());
                if(f->size() <= cutoff){
                    foundDirs.push_back(f);
                }
            }
            return foundDirs;
        }
        void addSubdir(Dir* f){
            f->setParent(this);
            subdirs.push_back(f);
        }
        void addSubfile(File* f){
            f->setParent(this);
            subfiles.push_back(f);
        }
        Dir* getSubdir(string n){
            for(Dir* f : subdirs)
                if(f->name == n)
                    return f;
            return nullptr;
        }
        File* getSubfile(string n){
            for(File* f : subfiles)
                if(f->name == n)
                    return f;
            return nullptr;
        }
        const vector<Dir*> getSubdirs(){return subdirs;}
        const vector<File*> getSubfiles(){return subfiles;}
        Dir(string n = ""){
            name.assign(n);
        }
        ~Dir(){
            for(Dir* f : subdirs)
                delete f;
            for(File* f : subfiles)
                delete f;
        }
    private:
        vector<Dir*> subdirs;
        vector<File*> subfiles;
};

void printFilesystem(Dir* root, string prefix = ""){

    cout << prefix << root->name << endl;
    for(Dir* subdir : root->getSubdirs())
        printFilesystem(subdir, prefix+"\t");
    for(File* subfile : root->getSubfiles())
        cout << prefix+"\t" << subfile->name << endl;
}

Dir* parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    Dir *root = new Dir(),
        *currentDir = root;

    string tmp, tmp2;
    inputStream >> tmp >> tmp2 >> root->name;
    int line = 0;
    while( (inputStream >> tmp) && !inputStream.eof()){

        if( !(tmp == "$") )
            abort();

        inputStream >> tmp;
        if(tmp == "cd"){
            inputStream >> tmp;
            currentDir = (tmp == "..") ? currentDir->getParent() : currentDir->getSubdir(tmp);
        }
        else if (tmp == "ls"){
            for(; (inputStream.peek() != '$') && !inputStream.eof(); inputStream.ignore()){
                inputStream >> tmp;
                if(tmp == "dir"){
                    inputStream >> tmp;
                    if(!currentDir->getSubdir(tmp))
                        currentDir->addSubdir(new Dir(tmp));
                }
                else{
                    inputStream >> tmp2;
                    if(!currentDir->getSubfile(tmp2))
                        currentDir->addSubfile(new File(tmp2, stoi(tmp)));
                }
            }
        }
        
            

    }

    inputStream.close();
    return root;
}

int main(){

    Dir* filesystem = parse(defaultFilePath);

    vector<int> sizes;
    for(Dir* f : filesystem->findBySize(100000))
        sizes.push_back(f->size());
    cout << "Sum of all directories with size at or below 100000: "
        << sum(sizes) << endl;

    int freeDiskSpace = 70000000 - filesystem->size();

    quickSort(sizes, 0, sizes.size()-1);

    int bestFile = INT_MAX;
    for(Dir* f : filesystem->findBySize())
        if(freeDiskSpace + f->size() > 30000000)
            if(bestFile > f->size())
                bestFile = f->size();
    cout << "Size of the smallest directory that frees up enough space to update: " << bestFile << endl;

    return 0;
}