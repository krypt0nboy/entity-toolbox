<?php

/**
 * Class LabelBuilder
 */
class LabelBuilder extends ValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }
}

/**
 * Class LabelBuilderSingle
 */
class LabelBuilderSingle extends LabelBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, 'single', $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    return entity_type2entity_label($this->entityType);
  }
}

/**
 * Class LabelBuilderPlural
 */
class LabelBuilderPlural extends LabelBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, 'plural', $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    return entity_type2entity_label_plural($this->entityType);
  }
}