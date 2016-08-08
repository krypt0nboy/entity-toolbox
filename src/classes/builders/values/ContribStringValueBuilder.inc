<?php

/**
 * Class ContribStringValueBuilder
 */
class ContribStringValueBuilder extends StringValueBuilder {
  /**
   * @var array $toolboxInfo
   *   The entity type toolbox info.
   */
  protected $toolboxInfo = array();

  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData, $defaultValue, $defaultValueIsTemplate, array $templateVariables) {
    parent::__construct($entityType, $tableKey, $rawData, $defaultValue, $defaultValueIsTemplate, $templateVariables);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
  }
}