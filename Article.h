#pragma once
#include <string>
#include <vector>

class Article {
private:
    std::vector<std::string> authors;
    std::string publicationName;
    std::string articleTitle;
    int year;

public:
    Article(const std::vector<std::string>& auth, const std::string& pubName,
        const std::string& artTitle, int yr);

    Article(const Article& other);

    Article(Article&& other) noexcept;

    ~Article();

    // Assignment operators
    Article& operator=(const Article& other);
    Article& operator=(Article&& other) noexcept;

    const std::vector<std::string>& getAuthors() const;
    std::string getPublicationName() const;
    std::string getArticleTitle() const;
    int getYear() const;

    void setAuthors(const std::vector<std::string>& auth);
    void setPublicationName(const std::string& pubName);
    void setArticleTitle(const std::string& artTitle);
    void setYear(int yr);

};