```mermaid
classDiagram
class Person {
    - name: String
}
class Address {
    - street: String
    - city: String
    - state: String
    - zip: String
}
Person "1" -- "1" Address

```