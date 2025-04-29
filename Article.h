#pragma once
#include <string>
#include <vector>

class Article {
private:
    std::vector<std::string> authors;
    std::string journalTitle;
    std::string articleTitle;
    int publicationYear;

public:
    // Constructors
    Article(const std::vector<std::string>& auth, const std::string& journal,
        const std::string& title, int year);

    // Copy constructor
    Article(const Article& other);

    // Move constructor
    Article(Article&& other) noexcept;

    // Destructor
    ~Article();

    // Assignment operators
    Article& operator=(const Article& other);
    Article& operator=(Article&& other) noexcept;

    // Getters
    const std::vector<std::string>& getAuthors() const;
    std::string getJournalTitle() const;
    std::string getArticleTitle() const;
    int getPublicationYear() const;

    // Setters
    void setAuthors(const std::vector<std::string>& auth);
    void setJournalTitle(const std::string& journal);
    void setArticleTitle(const std::string& title);
    void setPublicationYear(int year);
};