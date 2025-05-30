#include "Scientist.h"
#include <iostream>
#include <sstream>

Scientist::Scientist()
    : conferencePresentations(0), patentsCount(0), degree(AcademicDegree::NONE) {}

Scientist::Scientist(const std::vector<Article>& pubs, int presentations,
    int patents, AcademicDegree deg)
    : publications(pubs), conferencePresentations(presentations),
    patentsCount(patents), degree(deg) {}

Scientist::Scientist(const Scientist& other)
    : publications(other.publications), conferencePresentations(other.conferencePresentations),
    patentsCount(other.patentsCount), degree(other.degree) {}

Scientist::Scientist(Scientist&& other) noexcept
    : publications(std::move(other.publications)),
    conferencePresentations(other.conferencePresentations),
    patentsCount(other.patentsCount), degree(other.degree) {}

Scientist::~Scientist() {}

Scientist& Scientist::operator=(const Scientist& other) {
    if (this != &other) {
        publications = other.publications;
        conferencePresentations = other.conferencePresentations;
        patentsCount = other.patentsCount;
        degree = other.degree;
    }
    return *this;
}

Scientist& Scientist::operator=(Scientist&& other) noexcept {
    if (this != &other) {
        publications = std::move(other.publications);
        conferencePresentations = other.conferencePresentations;
        patentsCount = other.patentsCount;
        degree = other.degree;
    }
    return *this;
}




const std::vector<Article>& Scientist::getPublications() const { return publications; }
int Scientist::getConferencePresentations() const { return conferencePresentations; }
int Scientist::getPatentsCount() const { return patentsCount; }
AcademicDegree Scientist::getAcademicDegree() const { return degree; }

void Scientist::setPublications(const std::vector<Article>& pubs) { publications = pubs; }
void Scientist::setConferencePresentations(int presentations) {
    conferencePresentations = presentations;
}
void Scientist::setPatentsCount(int patents) { patentsCount = patents; }
void Scientist::setAcademicDegree(AcademicDegree deg) { degree = deg; }





void Scientist::addPublication(const Article& article) {
    publications.push_back(article);
}

void Scientist::removePublication(int index) {
    if (index >= 0 && index < publications.size()) {
        publications.erase(publications.begin() + index);
    }
}



std::ostream& operator<<(std::ostream& os, const Scientist& scientist) {
    os << "Publications:\n";
    for (const auto& pub : scientist.getPublications()) {
        os << "- " << pub.getArticleTitle() << " (" << pub.getPublicationYear() << ")\n";
    }
    os << "Conference presentations: " << scientist.getConferencePresentations() << "\n";
    os << "Patents count: " << scientist.getPatentsCount() << "\n";
    os << "Academic degree: ";
    switch (scientist.getAcademicDegree()) {
    case AcademicDegree::NONE: os << "None"; break;
    case AcademicDegree::CANDIDATE_TECH: os << "Candidate of Technical Sciences"; break;
    case AcademicDegree::CANDIDATE_PHYSMATH: os << "Candidate of Physical-Mathematical Sciences"; break;
    case AcademicDegree::PHD: os << "PhD"; break;
    case AcademicDegree::DOCTOR_TECH: os << "Doctor of Technical Sciences"; break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Scientist& scientist) {
    scientist.setPublications({});

    std::cout << "Enter scientific information:\n";
    std::cout << "Number of publications: ";
    int pubCount;
    is >> pubCount;
    is.ignore();

    for (int i = 0; i < pubCount; ++i) {
        std::vector<std::string> authors;
        std::string journal, title;
        int year;

        std::cout << "Publication #" << i + 1 << ":\n";
        std::cout << "Authors (comma separated): ";
        std::string authorsStr;
        std::getline(is, authorsStr);
        std::stringstream ss(authorsStr);
        std::string author;
        while (std::getline(ss, author, ',')) {
            author.erase(0, author.find_first_not_of(" \t"));
            author.erase(author.find_last_not_of(" \t") + 1);
            if (!author.empty()) authors.push_back(author);
        }

        std::cout << "Journal title: ";
        std::getline(is, journal);

        std::cout << "Article title: ";
        std::getline(is, title);

        std::cout << "Publication year: ";
        is >> year;
        is.ignore();

        scientist.addPublication(Article(authors, journal, title, year));
    }

    std::cout << "Number of conference presentations: ";
    int presentations;
    is >> presentations;
    scientist.setConferencePresentations(presentations);
    is.ignore();

    std::cout << "Number of patents: ";
    int patents;
    is >> patents;
    scientist.setPatentsCount(patents);
    is.ignore();

    std::cout << "Academic degree (0=None, 1=Candidate Tech, 2=Candidate PhysMath, 3=PhD, 4=Doctor Tech): ";
    int degree;
    is >> degree;
    scientist.setAcademicDegree(static_cast<AcademicDegree>(degree));
    is.ignore();

    return is;
}


void Scientist::displayInfo() const {
    std::cout << "--- Scientific Information ---\n";
    std::cout << "Publications: " << getPublications().size() << "\n";
    std::cout << "Conference presentations: " << getConferencePresentations() << "\n";
    std::cout << "Patents: " << getPatentsCount() << "\n";
    std::cout << "Degree: ";
    switch (getAcademicDegree()) {
    case AcademicDegree::NONE: std::cout << "None"; break;
    case AcademicDegree::CANDIDATE_TECH: std::cout << "Candidate Tech"; break;
    case AcademicDegree::CANDIDATE_PHYSMATH: std::cout << "Candidate PhysMath"; break;
    case AcademicDegree::PHD: std::cout << "PhD"; break;
    case AcademicDegree::DOCTOR_TECH: std::cout << "Doctor Tech"; break;
    }
    std::cout << "\n";
}