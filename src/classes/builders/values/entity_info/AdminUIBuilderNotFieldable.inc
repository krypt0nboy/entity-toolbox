<?php

/**
 * Class AdminUIBuilder
 */
class AdminUIBuilderNotFieldable extends AdminUIBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    parent::build();

    return $this->processedData;
  }
}