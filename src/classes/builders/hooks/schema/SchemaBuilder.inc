<?php

/**
 * Class SchemaBuilder
 */
class SchemaBuilder extends ContribHookBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType) {
    parent::__construct("schema", $entityType);
  }

  /** {{@inheritdoc}} */
  public function setValuesBuilders() {
    $this->valuesBuilders[$this->toolboxInfo['tables']['base']] = new SchemaBaseValueBuilder($this->entityType, $this->toolboxInfo['tables']['base']);
    if (!empty($this->toolboxInfo['tables']['revision'])) {
      $this->valuesBuilders[$this->toolboxInfo['tables']['revision']] = new SchemaBaseValueBuilder($this->entityType, $this->toolboxInfo['tables']['revision']);
    }
    if (!empty($this->toolboxInfo['tables']['relation'])) {
      foreach ($this->toolboxInfo['tables']['relation'] as $propertyName => $relationTable) {
        $this->valuesBuilders[$relationTable] = new SchemaBaseValueBuilder($this->entityType, $relationTable);
      }
    }
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData = $this->buildDefault();

    return $this->processedData;
  }

  /** {{@inheritdoc}} */
  protected function buildDefault() {
    $default = array();
    foreach ($this->getValuesBuilders() as $name => $builder) {
      $default[$name] = $builder->build();
    }

    return $default;
  }


}