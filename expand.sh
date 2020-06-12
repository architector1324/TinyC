#!/bin/bash

gcc -E $1 | sed '/^#/d'
