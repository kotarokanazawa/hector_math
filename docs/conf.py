#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os

# import sys
# sys.path.insert(0, os.path.abspath('.'))

from subprocess import call

call("doxygen")
call(["python3", "scripts/generate_coloring_images.py"])
# -- Project information -----------------------------------------------------

project = "hector_math"
copyright = "2019-2024, Stefan Fabian"
author = "Stefan Fabian"

# The short X.Y version
version = "1.0"
# The full version, including alpha/beta/rc tags
release = "1.0.0"

# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "breathe",
    "sphinx_rtd_theme",
    "sphinx.ext.viewcode",
    "sphinx.ext.githubpages",
]
todo_include_todos = True

# Breathe Configuration
breathe_projects = {"project": os.path.abspath("xml")}
breathe_default_project = "project"

# If true, current module path is prepended to all description unit titles
# such as functions
add_module_names = False

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []
master_doc = "index"

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
# html_theme = 'alabaster'
html_theme = "sphinx_rtd_theme"

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
# html_theme_options = {}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}


############################
# SETUP THE RTD LOWER-LEFT #
############################
try:
    html_context
except NameError:
    html_context = dict()
html_context["display_lower_left"] = True

if "REPO_NAME" in os.environ:
    REPO_NAME = os.environ["REPO_NAME"]
else:
    REPO_NAME = ""

# SET CURRENT_LANGUAGE
if "current_language" in os.environ:
    # get the current_language env var set by buildDocs.sh
    current_language = os.environ["current_language"]
else:
    # the user is probably doing `make html`
    # set this build's current language to english
    current_language = "en"

# tell the theme which language to we're currently building
html_context["current_language"] = current_language

# SET CURRENT_VERSION
if "current_version" in os.environ:
    # get the current_version env var set by buildDocs.sh
    current_version = os.environ["GITHUB_REF_NAME"]
else:
    try:
        from git import Repo

        repo = Repo(search_parent_directories=True)

        # the user is probably doing `make html`
        # set this build's current version by looking at the branch
        current_version = repo.active_branch.name
    except ImportError:
        current_version = "unknown"

# tell the theme which version we're currently on ('current_version' affects
# the lower-left rtd menu and 'version' affects the logo-area version)
html_context["current_version"] = current_version
html_context["version"] = current_version

# POPULATE LINKS TO OTHER LANGUAGES
html_context["languages"] = [("en", "/" + REPO_NAME + "/en/" + current_version + "/")]

# languages = [lang.name for lang in os.scandir('locales') if lang.is_dir()]
# for lang in languages:
#   html_context['languages'].append( (lang, '/' +REPO_NAME+ '/' +lang+ '/' +current_version+ '/') )

# POPULATE LINKS TO OTHER VERSIONS
html_context["versions"] = list()

versions = ["master"]  # documentation is just build for the master branch
for version in versions:
    html_context["versions"].append(
        (version, "/" + REPO_NAME + "/" + current_language + "/" + version + "/")
    )

# POPULATE LINKS TO OTHER FORMATS/DOWNLOADS

# settings for creating PDF with rinoh
rinoh_documents = [
    (
        master_doc,
        "target",
        project + " Documentation",
        "© " + copyright,
    )
]
today_fmt = "%B %d, %Y"

# settings for EPUB
epub_basename = "target"

html_context["downloads"] = list()
# html_context["downloads"].append(
#     (
#         "pdf",
#         "/"
#         + REPO_NAME
#         + "/"
#         + current_language
#         + "/"
#         + current_version
#         + "/"
#         + project
#         + "-docs_"
#         + current_language
#         + "_"
#         + current_version
#         + ".pdf",
#     )
# )

html_context["downloads"].append(
    (
        "epub",
        "/"
        + REPO_NAME
        + "/"
        + current_language
        + "/"
        + current_version
        + "/"
        + project
        + "-docs_"
        + current_language
        + "_"
        + current_version
        + ".epub",
    )
)

##########################
# "EDIT ON GITHUB" LINKS #
##########################

html_context["display_github"] = True
html_context["github_user"] = "tu-darmstadt-ros-pkg"
html_context["github_repo"] = "hector_math"
html_context["github_version"] = f"{current_version}/docs/"
