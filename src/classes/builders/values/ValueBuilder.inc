<?php


/**
 * Class ValueBuilder
 *
 * Used to build the value of an array key.
 */
class ValueBuilder extends BuilderBase {

  /**
   * @var mixed $rawValueData
   *   The isolated raw value data from $rawData.
   */
  protected $rawValueData;

  /**
   * @var mixed $processedValueData
   *   The processed value data to return.
   */
  protected $processedValueData;

  /**
   * @var string $tableKey
   *   The current key name.
   */
  protected $tableKey;

  /**
   * @var mixed $defaultValue
   *   The default value to be set. Can be a string template.
   *
   * @see string_template_process().
   */
  protected $defaultValue;

  /**
   * @var bool $defaultValueIsTemplate
   *   Indicates if the default value needs to be processed by string_process_template().
   */
  protected $defaultValueIsTemplate;

  /**
   * @var array $templateVariables
   *   An associative array containing the array passed to string_process_template().
   */
  protected $templateVariables = array();

  /**
   * ValueBuilder constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   * @param null|string $tableKey
   *   The current key name.
   * @param array       $rawData
   *   The passed raw data.
   * @param mixed       $defaultValue
   *   The default value to be set if needed.
   * @param bool        $defaultValueIsTemplate
   *   Indicates if the default value should be processed as a template.
   * @param array       $templateVariables
   *   The variables to be accessed by string_process_template when processing the default value.
   */
  public function __construct($entityType = NULL, $tableKey = NULL, array $rawData = array(), $defaultValue = NULL, $defaultValueIsTemplate = NULL, array $templateVariables = array()) {
	parent::__construct($entityType, $rawData);
	if (!isset($tableKey)) {
	  //throw exception
	}
	$this->tableKey = $tableKey;
	if (isset($defaultValue)) {
	  $this->defaultValue           = $defaultValue;
	  $this->defaultValueIsTemplate = isset($defaultValueIsTemplate) ? $defaultValueIsTemplate : preg_match('/%\w+%/', $defaultValue);
	}
  }

  /**
   * Builds the value.
   *
   * @return mixed
   */
  public function build() {
	$this->processedValueData = $this->valueIsNull() ? NULL : $this->buildDefault();

	return $this->processedValueData;
  }

  /**
   * Builds the default value to be merged in the method build().
   *
   * @return mixed
   */
  protected function buildDefault() {
	return $this->defaultValueIsTemplate ? string_template_process($this->defaultValue, $this->templateVariables) : $this->defaultValue;
  }

  /**
   * Determines how the value is considered to be excluded from buildDefault().
   *
   * @return bool
   */
  protected function valueIsNull() {
	return $this->rawData[$this->tableKey] === FALSE;
  }
}

