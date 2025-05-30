#pragma once
#include <string>
#include <vector>
#include <stdexcept> 

class Article {
private:
    std::vector<std::string> authors;
    std::string journalTitle;
    std::string articleTitle;
    int publicationYear;

    bool isValidYear(int year) const;

public:
    Article(const std::vector<std::string>& auth, const std::string& journal,
        const std::string& title, int year);

    Article(const Article& other);
    Article(Article&& other) noexcept;

    ~Article();

    Article& operator=(const Article& other);
    Article& operator=(Article&& other) noexcept;

    const std::vector<std::string>& getAuthors() const;
    std::string getJournalTitle() const;
    std::string getArticleTitle() const;
    int getPublicationYear() const;

    void setAuthors(const std::vector<std::string>& auth);
    void setJournalTitle(const std::string& journal);
    void setArticleTitle(const std::string& title);
    void setPublicationYear(int year);
};