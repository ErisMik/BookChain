FROM python:3.7

ENV FLASK_APP app.py

RUN mkdir -p /usr/bookchain
WORKDIR /usr/bookchain

RUN apt-get update -y && apt-get install -y cmake

COPY requirements.txt /usr/bookchain/
RUN pip install -r requirements.txt

COPY src/ /usr/bookchain/

EXPOSE 5000
CMD ["python", "app.py"]
