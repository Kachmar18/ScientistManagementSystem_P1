#pragma once
#include "Article.h"
#include "AcademicDegree.h"
#include <vector>

class Scientist {
private:
    std::vector<Article> publications;
    int conferencePresentations;
    int patentsCount;
    AcademicDegree degree;

public:
    Scientist();

    Scientist(const std::vector<Article>& pubs, int presentations,
        int patents, AcademicDegree deg);
    Scientist(const Scientist& other);
    Scientist(Scientist&& other) noexcept;

    ~Scientist();

    Scientist& operator=(const Scientist& other);
    Scientist& operator=(Scientist&& other) noexcept;

    const std::vector<Article>& getPublications() const;
    int getConferencePresentations() const;
    int getPatentsCount() const;
    AcademicDegree getAcademicDegree() const;

    void setPublications(const std::vector<Article>& pubs);
    void setConferencePresentations(int presentations);
    void setPatentsCount(int patents);
    void setAcademicDegree(AcademicDegree deg);

    void addPublication(const Article& article);
    void removePublication(int index);


    friend std::ostream& operator<<(std::ostream& os, const Scientist& scientist);
    friend std::istream& operator>>(std::istream& is, Scientist& scientist);

    virtual void displayInfo() const;
};