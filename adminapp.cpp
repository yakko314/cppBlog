#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include <chrono>
#include <ctime>


#include "shared/classes/Comment.h"
#include "shared/classes/Post.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


using namespace std;

ifstream f;
ofstream g;

vector<Post> posts; ///< Toate postarile de pe blog.
unordered_map<int, int> idToIndex; ///< Un map pe care il folosim pentru a face conversia din ID in index din lista

int nrPosts = 0; ///< variabila ajutatoare pentru nr de postari
int nrComments = 0; ///< variabila ajutatoare pentru nr de comentarii
/**
 * @brief Citeste toate datele relevante si le include in clase cu care putem lucra
 */
void read() 
{
    f.open("shared/files/Postari.txt");
    if(!f) {
        cerr << RED "Nu exista fisierul cu " MAGENTA "postari" RED "! Datele afisate pot fi gresite!\n" RESET;
        return;
    }
    f >> nrPosts;
    for (int i = 0; i < nrPosts; i++) 
    {
        int id;
        string title;
        string file;
        string content;
        f >> id;
        f.ignore();
        getline(f, title);
        getline(f, file);
        getline(f, content);
        idToIndex[id] = posts.size();

        int day;
        int month;
        int year;
        f >> day >> month >> year;

        Date date(day,month,year);
        Post post(id,title,file,content,date);

        posts.push_back(post);
    }
    f.close();

    f.open("shared/files/Comentarii.txt");
    if(!f) {
        cerr << RED "Nu exista fisierul cu " YELLOW "comentarii" RED "! Datele afisate pot fi gresite!\n" RESET;
        return;
    }
    string content;
    f >> nrComments;
    for (int i = 0; i < nrComments; i++) 
    {
        int x;
        f>>x;
        f.ignore();
        string username;
        getline(f, username);
        getline(f, content);
        int day, month, year;
        f >> day >> month >> year;
        if (idToIndex.count(x)) 
        {
            Date date(day,month,year);
            Comment comment(username,content,date);
            // std::cout << "Adding comment to post " << x << ": \"" << content << "\" by " << username << " on " << date << "\n";
            posts[idToIndex[x]].addComment(comment);
        }
    }

    f.close();

    f.open("shared/files/Statistici.txt");
    if(!f) {
        cerr << RED "Nu exista fisierul cu " GREEN "interactiuni" RED "! Datele afisate pot fi gresite!\n" RESET;
        return;
    }
    int nrInteractiuni;
    f >> nrInteractiuni;
    for (int i = 0; i < nrInteractiuni; i++) 
    {
        int x;
        f>>x;
        if (idToIndex.count(x)) 
        {
            int like, dislike, love;
            f >> like >> dislike >> love;
            Stats stats(like,dislike,love);
            posts[idToIndex[x]].setStats(stats);

        } else 
        {
            unsigned int tmp1, tmp2, tmp3;
            f >> tmp1 >> tmp2 >> tmp3;
        }
    }
    f.close();
}

/**
 * @brief Sterge interactiunile de la o postare
 */
void deleteStats(int index) 
{
    int nrInteractiuni = 0;
    for (const auto& p : posts) 
    {
        if (p.getStats().getLike() != 0 || p.getStats().getDislike() != 0 || p.getStats().getLove() != 0) 
        {
            if(p.getId()!=posts[index].getId())
                nrInteractiuni++;
        }
    }
    g.open("shared/files/Statistici.txt");
    g << nrInteractiuni << "\n\n";
    for (const auto& p : posts) 
    {
        if (p.getId()!=posts[index].getId() && (p.getStats().getLike() != 0 || p.getStats().getDislike() != 0 || p.getStats().getLove() != 0))
        {
            g << p.getId() << '\n';
            g << p.getStats().getLike() << ' '
            << p.getStats().getDislike() << ' '
            << p.getStats().getLove() << '\n';
            g << '\n';
        }

    }
    g.close();
}

/**
 * @brief Sterge comentariile de la o postare
 */
void deleteComments(int index) 
{
    g.open("shared/files/Comentarii.txt");
    nrComments-=posts[index].getComments().size();
    int id=posts[index].getId();
    g << nrComments << "\n\n";
    for (const auto& p : posts) 
    {
        if (!p.getComments().empty() && p.getId()!=id) 
        {
            for (const auto& c : p.getComments()) 
            {
                g << p.getId() << '\n';
                g << c.getUsername() << '\n';
                g << c.getContent() << '\n';
                g << c.getDate().getDay() << ' ';
                g << c.getDate().getMonth() << ' ';
                g << c.getDate().getYear() << '\n';
                g << "\n";
            }

        }
    }
    g.close();
}
/**
 * @brief Rescrie in fisierul de postari toate postarile
 */
void writeposts()
{
    g.open("shared/files/Postari.txt");
    g<< posts.size()<<"\n";
    for(int i=0;i<posts.size();i++)
    {
        g<<posts[i].getId()<<'\n';
        g<<posts[i].getTitle()<<'\n';
        g<<posts[i].getFile()<<'\n';
        g<<posts[i].getContent()<<'\n';
        g<<posts[i].getDate().getDay()<<' ';
        g<<posts[i].getDate().getMonth()<<' ';
        g<<posts[i].getDate().getYear()<<'\n';
        if(i!=posts.size()-1)
            g<<"\n";
    }
    g.close();
}

/**
 * O functie template care calculeaza valuarea procentuala fata de un total
 * @param value valuarea pentru care se doreste calculat procentul
 * @param total totalul fata de care se calculeaza procentul
 */
template<typename T> double precent(T value,T total)
{
    if(total==0) return 0.0;
    return (static_cast<double>(value)/total)*100.0;
}

/**
 * O functie care afiseaza statistica unei postari
 * @param index este indexul postarii pentru statistica
 */
void postprecent(int index)
{
    unsigned int total=posts[index].getStats().getDislike()+posts[index].getStats().getLike()+posts[index].getStats().getLove();
    cout<<BLUE<<"Statisticile postarii" RESET ": \n"<<GREEN<<"+"<<precent(posts[index].getStats().getLike(),total)<<"%"<<RESET<<" | "
    <<CYAN<<"-"<<precent(posts[index].getStats().getDislike(),total)<<"%"<<RESET<<" | "
    <<RED<<precent(posts[index].getStats().getLove(),total)<<"%"<<" <3"<<RESET<<"\n";
}

/**
 * @brief O functie care afiseaza distributia procentuala a blogului
 */
void precentdistribution()
{
    double sumLike=0.0;
    double sumDislike=0.0;
    double sumLove=0.0;
    for(int i=0;i<posts.size();i++)
    {
        unsigned int total=posts[i].getStats().getDislike()+posts[i].getStats().getLike()+posts[i].getStats().getLove();
        if(total==0) continue;
        sumLike+=precent(posts[i].getStats().getLike(),total);
        sumDislike+=precent(posts[i].getStats().getDislike(),total);
        sumLove+=precent(posts[i].getStats().getLove(),total);
    }
    double totalPrecent=sumDislike+sumLike+sumLove;
    cout<< BLUE "Distributia procentuala a statisticilor" RESET ": \n"<<GREEN<<"+"<<precent(sumLike,totalPrecent)<<"%"<<RESET<<" | "<<CYAN<<"-"<<precent(sumDislike,totalPrecent)
    <<"% "<<RESET<<"| "<<RED<<precent(sumLove,totalPrecent)<<"% <3\n"<<RESET;
}

/**
 * @brief Cauta cel mai mic id care nu este folosit
 */
int idnou()
{
    int i=0,ok=0,da=0;
    while(!ok)
    {
        da=1;
        for(int j=0;j<posts.size();j++)
        {
            if(posts[j].getId()==i)
            {
                da=0;
                i++;
            }
        }
        if(da==1)
        {
            ok=1;
        }
    }
    return  i;
}

/**
 * O functie care determina daca fisierul introdus are extensia corespunzatoare
 * @param fisier este stringul in care se va cauta extensia
 * @param ext este extensia cautata
 */
bool extensie( string fisier, string ext)
{
    return fisier.size()>=ext.size() && fisier.compare(fisier.size()-ext.size(),ext.size(),ext) == 0;
}

/**
 * @brief Afiseaza toate comenzile posibile
 */
void cmdHelp() 
{
    cout << CYAN "~Sistem de blog: Admin~\n" RESET
    << GREEN "vizualizare_comentarii <numar_postare>" RESET " - arata toate comantariile unei postari;\n"
    << GREEN "vizualizare_interactiuni <numar_postare>" RESET" - arata toate interactiunile unei postari;\n"
    << GREEN "postare_noua <titlu_postare> <continut_postare> [file]" RESET " - adauga o postare noua;\n"
    << GREEN "editare_postare <numar_postare> <titlu|continut|fisier> <content_nou>" RESET " - editeaza contentul unei postari;\n"
    << GREEN "sterge_postare <numar_postare>" RESET " - sterge o postare;\n"
    << GREEN "statistici_postare <numar_postare>" RESET " - procentul de like, dislike si love ale unei postari;\n"
    << GREEN "statistici_postari" RESET " - distributia procentuala a statisticilor per postare;\n";
}

/**
 * @brief Semnaleaza lipsa unei postari la un anume index.
 */
void noPost() 
{
    cout << RED "Postarea nu exista!\n" RESET;
}

/**
 * O functie care valideaza extensia de la un file
 * @param file este stringul pentru care verifica extensia
 */
bool validatefile(string file)
{
    if(!extensie(file,".mp4") && !extensie(file,".mp3") && !extensie(file,".jpg") && !extensie(file,".png"))
    {
        cout<<RED<<"Fisierul nu contine o extensie valida\n"<<RESET;
        cout<<BLUE<<"Extensiile Valde: "<<RESET<<" .mp4; .mp3; .jpg; .png;\n";
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    read();
    if (argc == 1) 
    {
        cmdHelp();
        return 0;
    }
    string command = argv[1];
    if(command=="help")
    {
        cmdHelp();
        return 0;
    }
    if (command=="vizualizare_comentarii") 
    {
        if(argc<3)
        {
            cout<< GREEN "Utilizare: " RESET "vizualizare_comentarii <numar_postare>\n";
            return 0;
        }
        int index=stoi(argv[2])-1;
        if(index<0 || index>=posts.size())
        {
            noPost();
            return 0;
        }
        posts[index].commentPrint(cout);
        return 0;
    }
    if(command=="vizualizare_interactiuni")
    {
        if(argc<3)
        {
            cout<< GREEN "Utilizare: " RESET "vizualizare_interactiuni <numar_postare>\n";
            return 0;
        }
        int index=stoi(argv[2])-1;
        if(index<0 || index>=posts.size())
        {
            noPost();
            return 0;
        }
        posts[index].interactionPrint(cout);
        return 0;
    }
    if(command=="postare_noua")
    {
        if(argc<4)
        {
            cout<< GREEN "Utilizare: " RESET "postare_noua <titlu_postare> <continut_postare> [file]\n";
            return 0;
        }

        //Extragem data curenta
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        tm* local_tm = localtime(&now_time);
        int day = local_tm->tm_mday;
        int month = local_tm->tm_mon + 1;
        int year = local_tm->tm_year + 1900;
        Date data(day,month,year);
        int id=idnou();
        string title=argv[2];
        string content=argv[3];
        string file;
        if(argc>4)
        {
            file=argv[4];
            if(!validatefile(file))
                return 0;
        }
        else
            file="NONE";
        Post newpost(id,title,file,content,data);
        posts.push_back(newpost);
        cout<<"Postarea cu numele " << BLUE<< title <<RESET<<" a fost adaugata cu succes!\n";
        writeposts();
        return 0;
    }
    if(command=="editare_postare")
    {
        if(argc<5)
        {
            cout<< GREEN "Utilizare: " RESET "editare_postare <numar_postare> <titlu|continut|fisier> <content_nou>\n";
            return 0;
        }
        int index=stoi(argv[2])-1;
        if(index<0 || index>=posts.size())
        {
            noPost();
            return 0;
        }
        string edit=argv[3];
        if(edit=="continut")
        {
            string content=argv[4];
            posts[index].editcontent(content);
            cout<<"Continutul postarii a fost editat cu success!\n";
            writeposts();
            return 0;
        }
        if(edit=="titlu")
        {
            string title=argv[4];
            posts[index].edittitle(title);
            cout<< MAGENTA "Titlul " RESET " postarii a fost editata cu success!\n";
            writeposts();
            return 0;
        }
        if(edit=="fisier")
        {
            string file=argv[4];
            if(!validatefile(file))
                return 0;
            posts[index].editfile(file);
            cout<< RED "Fisierul " RESET " postarii a fost editat cu success!\n";
            writeposts();
            return 0;
        }
        else
        {
            cout<< GREEN "Utilizare: " RESET "editare_postare <numar_postare> <titlu|continut|fisier> <content_nou>\n";
            return 0;
        }
    }
    if(command=="sterge_postare")
    {
        if(argc<3)
        {
            cout<< GREEN "Utilizare: " RESET "sterge_postare <numar_postare>\n";
            return 0;
        }
        int index=stoi(argv[2])-1;
        if(index<0 || index>=posts.size())
        {
            noPost();
            return 0;
        }
        int id=posts[index].getId();
        deleteComments(index);
        deleteStats(index);
        posts.erase(posts.begin()+index);
        cout<<"Postarea a fost " RED "stearsa" RESET " cu success!\n";
        writeposts();
        return 0;
    }
    if(command=="statistici_postare")
    {
        if(argc<3)
        {
            cout<< GREEN "Utilizare: " RESET "statistici_postare <numar_postare>\n";
            return 0;
        }
        int index=stoi(argv[2])-1;
        if(index<0 || index>=posts.size())
        {
            noPost();
            return 0;
        }
        postprecent(index);
        return 0;
    }
    if(command=="statistici_postari")
    {
        precentdistribution();
        return 0;
    }
    cout<<RED<<"Comanda nu exista!\n"<< RESET << "Foloseste comanda " GREEN "help" RESET " pentru comenzile disponibile.\n";
    return 0;
}