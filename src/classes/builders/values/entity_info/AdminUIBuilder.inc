<?php

/**
 * Class AdminUIBuilder
 */
class AdminUIBuilder extends ArrayValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, "admin ui", $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    
  }
}