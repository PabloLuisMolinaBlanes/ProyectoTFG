FROM node:latest
WORKDIR /app

COPY package.json .
COPY tsconfig.json .
RUN node install

COPY . .

CMD ["node", "run"]