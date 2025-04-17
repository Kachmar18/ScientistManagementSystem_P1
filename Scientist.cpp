#include "Scientist.h"

Scientist::Scientist(const std::vector<Article>& pubs, int confPres,
    int patents, Degree degree)
    : publications(pubs), conferencePresentations(confPres),
    patentsCount(patents), academicDegree(degree) {}

Scientist::Scientist(const Scientist& other)
    : publications(other.publications),
    conferencePresentations(other.conferencePresentations),
    patentsCount(other.patentsCount),
    academicDegree(other.academicDegree) {}

Scientist::Scientist(Scientist&& other) noexcept
    : publications(std::move(other.publications)),
    conferencePresentations(other.conferencePresentations),
    patentsCount(other.patentsCount),
    academicDegree(other.academicDegree) {}

// Copy assignment operator
Scientist& Scientist::operator=(const Scientist& other) {
    if (this != &other) {
        publications = other.publications;
        conferencePresentations = other.conferencePresentations;
        patentsCount = other.patentsCount;
        academicDegree = other.academicDegree;
    }
    return *this;
}

// Move assignment operator
Scientist& Scientist::operator=(Scientist&& other) noexcept {
    if (this != &other) {
        publications = std::move(other.publications);
        conferencePresentations = other.conferencePresentations;
        patentsCount = other.patentsCount;
        academicDegree = other.academicDegree;
    }
    return *this;
}

const std::vector<Article>& Scientist::getPublications() const {
    return publications;
}

int Scientist::getConferencePresentations() const {
    return conferencePresentations;
}

int Scientist::getPatentsCount() const {
    return patentsCount;
}

Degree Scientist::getAcademicDegree() const {
    return academicDegree;
}

void Scientist::setPublications(const std::vector<Article>& pubs) {
    publications = pubs;
}

void Scientist::setConferencePresentations(int count) {
    conferencePresentations = count;
}

void Scientist::setPatentsCount(int count) {
    patentsCount = count;
}

void Scientist::setAcademicDegree(Degree degree) {
    academicDegree = degree;
}

void Scientist::addPublication(const Article& article) {
    publications.push_back(article);
}

void Scientist::removePublication(int index) {
    if (index >= 0 && index < publications.size()) {
        publications.erase(publications.begin() + index);
    }
}

std::ostream& operator<<(std::ostream& os, const Scientist& scientist) {
    scientist.printInfo(os);
    return os;
}
