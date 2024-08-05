(ns gabiwork.cats
  (:require [datomic.api :as d]))

(def db-uri "datomic:mem://gabiwork.cat")

;; Criar o banco de dados
(d/create-database db-uri)

;; Conectar ao banco de dados
(def conn (d/connect db-uri))
(println conn)

;; Definir esquema
(def schema-tx-data [{:db/ident :name
                      :db/valueType :db.type/string
                      :db/cardinality :db.cardinality/one
                      :db/doc "Cat's name"}
                     {:db/ident :peso
                      :db/valueType :db.type/float
                      :db/cardinality :db.cardinality/one
                      :db/doc "cat weight"}
                     {:db/ident :numbereat
                      :db/valueType :db.type/long
                      :db/cardinality :db.cardinality/one
                      :db/doc "How many times can he eat"}
                     {:db/ident :time
                      :db/valueType :db.type/string
                      :db/cardinality :db.cardinality/one
                      :db/doc "What time should he eat?"}])

;; Transacionar esquema
@(d/transact conn  schema-tx-data)

;; Definir dados dos gatos
(def draco
  {:name "draco"
   :peso 3.200
   :numbereat 1
   :time "manha"})

(def zeus
  {:name "zeus"
   :peso 4.500
   :numbereat 1
   :time "manha"})

;; Transacionar dados dos gatos
@(d/transact conn schema-tx-data)

;; Consultar dados dos gatos
(def result
  (d/q '[:find ?peso
         :where
         [?e :name "draco"]
         [?e :peso ?peso]]
       (d/db conn)))
(println result draco)

;; estudando a baixo

[[:db/cas draco :numbereat 1 2]]

(d/transact conn [[:db/cas draco :numbereat 1 2]])

(println draco)
