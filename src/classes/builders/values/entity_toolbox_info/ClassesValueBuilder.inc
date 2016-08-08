<?php

/**
 * Class ClassesValueBuilder
 */
class ClassesValueBuilder extends ArrayValueBuilder {
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, "classes", $rawData);
  }
}