#pragma once
#include "Article.h"
#include "Degree.h"
#include <vector>
#include <iostream>
#include <ostream> 

class Scientist{
    friend class ResearchTeachingStaff;
private:
    std::vector<Article> publications;
    int conferencePresentations;
    int patentsCount;
    Degree academicDegree;

protected:
    const std::vector<Article>& getPublicationsInternal() const { return publications; }
    int getConferencePresentationsInternal() const { return conferencePresentations; }
    int getPatentsCountInternal() const { return patentsCount; }
    Degree getAcademicDegreeInternal() const { return academicDegree; }

public:
    Scientist(const std::vector<Article>& pubs, int confPres,
        int patents, Degree degree);

    Scientist(const Scientist& other);
    Scientist(Scientist&& other) noexcept;

    virtual void printInfo(std::ostream& os) const {
        os << "Research Info:\n"
            << "  Publications: " << publications.size() << "\n"
            << "  Conference Presentations: " << conferencePresentations << "\n"
            << "  Patents: " << patentsCount << "\n"
            << "  Degree: ";
        switch (academicDegree) {
        case Degree::NONE: os << "None"; break;
        case Degree::CANDIDATE_TECHNICAL: os << "Candidate of Technical Sciences"; break;
        case Degree::CANDIDATE_PHYSICAL_MATHEMATICAL: os << "Candidate of Physical-Mathematical Sciences"; break;
        case Degree::PHD: os << "PhD"; break;
        case Degree::DOCTOR_TECHNICAL: os << "Doctor of Technical Sciences"; break;
        }
    }

    virtual ~Scientist() = default;

    Scientist& operator=(const Scientist& other);
    Scientist& operator=(Scientist&& other) noexcept;

    const std::vector<Article>& getPublications() const;
    int getConferencePresentations() const;
    int getPatentsCount() const;
    Degree getAcademicDegree() const;

    void setPublications(const std::vector<Article>& pubs);
    void setConferencePresentations(int count);
    void setPatentsCount(int count);
    void setAcademicDegree(Degree degree);

    void addPublication(const Article& article);
    void removePublication(int index);

    friend std::ostream& operator<<(std::ostream& os, const Scientist& scientist);
};