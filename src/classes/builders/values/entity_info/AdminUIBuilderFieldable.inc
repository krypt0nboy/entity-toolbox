<?php

/**
 * Class AdminUIBuilder
 */
class AdminUIBuilderFieldable extends AdminUIBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData                  = parent::build();
    $this->processedData['menu wildcard'] = "%$this->entityType";
  }
}