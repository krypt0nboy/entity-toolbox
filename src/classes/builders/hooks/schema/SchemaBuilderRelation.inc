<?php

/**
 * Created by PhpStorm.
 * User: ddoucoure
 * Date: 08/08/16
 * Time: 10:56
 */

class SchemaBuilderRelation extends SchemaBuilder {
  
  function __construct($entity_type , array $values) {
    parent::__construct($entity_type , $values);
  }
  
  function build() {
    $this->processedData = array($this->entityType => $this->buildDefault());
  }
  
  protected function buildDefault() {
    return array(
      'revision' => $this->defaultSchemaBuilderRelation(),
    );
  }
  
  private function populate(){
    if( !isset($this->rawData)){
      $this->rawData = $this->buildDefault();
    }
  }
}