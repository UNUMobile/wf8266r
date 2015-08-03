GitBook YouTube Plugin
===

This is a plugin for inserting YouTube videos in GitBook.

## Usage

Youtube videos can be inserted into a gitbook chapter using a tag with the video id inserted inbetween:

```
{%youtube%}dQw4w9WgXcQ{%endyoutube%}
```

See the plugin at work here: [Click here](http://ymcatar.gitbooks.io/gitbook-test/content/testing_youtubex.html)

## Changelog

* 0.3 Releases:
	* **0.3.0:** Added check to terminate the book generation if the id contain invalid characters.

* 0.2 Releases:
	* **0.2.1:** Fixed broken link in the documentation.
	* **0.2.0:** Improved looks and feels.

## Feature

* The player will be responsive and will resize according to the page size.
* A link pointing to the video will be displayed instead if the book is converted into .pdf or other ebook formats.
