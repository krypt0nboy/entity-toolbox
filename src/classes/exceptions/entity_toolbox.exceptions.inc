<?php

/**
 * Class EntityToolboxException
 */
class EntityToolboxException extends Exception {
  /**
   * @var string $template
   *   The message unprocessed template.
   *   (Eg : "Cannot instanciate %class%").
   */
  protected $template;

  /**
   * @var string[] $variables
   *   An array of string to replace matching tokens in the message.
   */
  protected $variables;

  /**
   * EntityToolboxException constructor.
   * @param string          $template
   * @param int             $code
   * @param array           $variables
   * @param null|\Exception $previous
   */
  public function __construct($template = "", $code = 0, $variables = array(), Exception $previous = NULL) {
	$this->template = $template;
	parent::__construct($template, $code, $previous);
	$this->message = string_template_process($this->template, $variables);
  }
}

/**
 * Class MissingEntityTypeException
 */
class MissingEntityTypeException extends EntityToolboxException {
  /**
   * MissingEntityTypeException constructor.
   * @param array          $variables
   * @param null|Exception $previous
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
	$template = "Cannot create an instance of %class% without a specified entity type.";
	parent::__construct($template, 101, $variables, $previous);
  }
}

/**
 * Class MissingRawToolboxInfoException
 */
class ToolboxInfoNotProvidedException extends EntityToolboxException {
  /**
   * MissingRawToolboxInfoException constructor.
   * @param array          $variables
   * @param null|Exception $previous
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
	$template = "Toolbox info not provided.";
	parent::__construct($template, 102, $variables, $previous);
  }
}

/**
 * Class MissingRawToolboxInfoException
 */
class MissingRawToolboxInfoException extends EntityToolboxException {
  /**
   * MissingRawToolboxInfoException constructor.
   * @param array          $variables
   * @param null|Exception $previous
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
	$template = "Entity type raw info not set.";
	parent::__construct($template, 103, $variables, $previous);
  }
}