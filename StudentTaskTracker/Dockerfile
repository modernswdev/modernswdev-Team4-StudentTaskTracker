FROM alpine:3.24

RUN apk add --no-cache g++

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -Iinclude src/StudentTaskTracker.cpp src/Task.cpp -o StudentTaskTracker

CMD ["./StudentTaskTracker"]