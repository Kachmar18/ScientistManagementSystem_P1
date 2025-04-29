#include "Article.h"

Article::Article(const std::vector<std::string>& auth, const std::string& journal,
    const std::string& title, int year)
    : authors(auth), journalTitle(journal), articleTitle(title), publicationYear(year) {}

Article::Article(const Article& other)
    : authors(other.authors), journalTitle(other.journalTitle),
    articleTitle(other.articleTitle), publicationYear(other.publicationYear) {}

Article::Article(Article&& other) noexcept
    : authors(std::move(other.authors)), journalTitle(std::move(other.journalTitle)),
    articleTitle(std::move(other.articleTitle)), publicationYear(other.publicationYear) {}

Article::~Article() {}

// Assignment operators
Article& Article::operator=(const Article& other) {
    if (this != &other) {
        authors = other.authors;
        journalTitle = other.journalTitle;
        articleTitle = other.articleTitle;
        publicationYear = other.publicationYear;
    }
    return *this;
}

Article& Article::operator=(Article&& other) noexcept {
    if (this != &other) {
        authors = std::move(other.authors);
        journalTitle = std::move(other.journalTitle);
        articleTitle = std::move(other.articleTitle);
        publicationYear = other.publicationYear;
    }
    return *this;
}


// Getters
const std::vector<std::string>& Article::getAuthors() const { return authors; }
std::string Article::getJournalTitle() const { return journalTitle; }
std::string Article::getArticleTitle() const { return articleTitle; }
int Article::getPublicationYear() const { return publicationYear; }

// Setters
void Article::setAuthors(const std::vector<std::string>& auth) { authors = auth; }
void Article::setJournalTitle(const std::string& journal) { journalTitle = journal; }
void Article::setArticleTitle(const std::string& title) { articleTitle = title; }
void Article::setPublicationYear(int year) { publicationYear = year; }