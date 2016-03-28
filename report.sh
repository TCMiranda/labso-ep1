#!/bin/bash

(./dist/main > report.txt; cat report.txt | more)
