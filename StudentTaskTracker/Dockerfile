FROM alpine:3.24

RUN apk add --no-cache \
    g++ \
    mariadb-connector-c-dev

WORKDIR /app

COPY . .

RUN g++ -std=c++17 \
    -Iinclude \
    -I/usr/include/mysql \
    src/StudentTaskTracker.cpp \
    src/Task.cpp \
    src/Database.cpp \
    -o StudentTaskTracker \
    -lmariadb

CMD ["./StudentTaskTracker"]
